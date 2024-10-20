# Base arguments
ARG LINUX_DISTRO=""
ARG DAOS_DOCKER_IMAGE_NSP=""
ARG DAOS_DOCKER_IMAGE_TAG=""

# Use the DAOS base image
FROM "${DAOS_DOCKER_IMAGE_NSP}/daos-base-${LINUX_DISTRO}:${DAOS_DOCKER_IMAGE_TAG}"
LABEL maintainer="daos@daos.groups.io"

# Build arguments
ARG DAOS_VERSION=""
ARG DAOS_AUTH=""
ARG DAOS_AGENT_IFACE_CFG=""
ARG DAOS_AGENT_IFACE_NUMA_NODE=""
ARG DAOS_AGENT_IFACE_NAME=""
ARG DAOS_AGENT_IFACE_DOMAIN_NAME=""

# Install DAOS client package and IO500 dependencies
RUN for it in DAOS_VERSION DAOS_AUTH DAOS_AGENT_IFACE_CFG DAOS_AGENT_IFACE_NUMA_NODE DAOS_AGENT_IFACE_NAME DAOS_AGENT_IFACE_DOMAIN_NAME ; do \
        if eval "[[ -z \$$it ]]" ; then \
            echo "[ERROR] Docker build argument $it is not defined" ; \
            exit 1 ; \
        fi ; \
    done && \
    dnf install -y \
        daos-client-${DAOS_VERSION} \
        git \
        gcc \
        gcc-c++ \
        vim \
        make \
        openmpi \
        openmpi-devel \
        libyaml-devel \
        hwloc-devel \
        numactl-devel \
        libaio-devel \
        python3 \
        autoconf \
        automake \
        libtool \
        && dnf clean all && \
    systemctl enable daos_agent

# Set OpenMPI environment variables
ENV PATH="/usr/lib64/openmpi/bin:${PATH}"
ENV LD_LIBRARY_PATH="/usr/lib64/openmpi/lib:${LD_LIBRARY_PATH}"

# Copy the DAOS agent configuration template
COPY daos_agent.yml.in /tmp/daos_agent.yml.in

# Configure DAOS agent
RUN if [ "$DAOS_AUTH" == "yes" ] ; then \
        sed --in-place --regexp-extended \
            --expression '/^@DAOS_NOAUTH_BEGIN@$/,/^@DAOS_NOAUTH_END@/d' \
            --expression '/(^@DAOS_AUTH_BEGIN@$)|(^@DAOS_AUTH_END@$)/d' \
            /tmp/daos_agent.yml.in && \
        chmod 644 /root/daosCA/certs/daosCA.crt && \
        chmod 644 /root/daosCA/certs/agent.crt && \
        chmod 400 /root/daosCA/certs/agent.key && \
        chown root:root /root/daosCA/certs/daosCA.crt && \
        chown daos_agent:daos_agent /root/daosCA/certs/agent.crt && \
        chown daos_agent:daos_agent /root/daosCA/certs/agent.key && \
        mv /root/daosCA/certs/daosCA.crt /etc/daos/certs/. && \
        mv /root/daosCA/certs/agent.crt /etc/daos/certs/. && \
        mv /root/daosCA/certs/agent.key /etc/daos/certs/. && \
        rm -fr /root/daosCA ; \
    else \
        sed --in-place --regexp-extended \
            --expression '/^@DAOS_AUTH_BEGIN@$/,/^@DAOS_AUTH_END@/d' \
            --expression '/(^@DAOS_NOAUTH_BEGIN@$)|(^@DAOS_NOAUTH_END@$)/d' \
            /tmp/daos_agent.yml.in ; \
    fi && \
    if [ "${DAOS_AGENT_IFACE_CFG}" == "yes" ] ; then \
        sed --in-place --regexp-extended \
            --expression '/(^@DAOS_IFACE_BEGIN@$)|(^@DAOS_IFACE_END@$)/d' \
            --expression "s/@DAOS_IFACE_NUMA_NODE@/${DAOS_AGENT_IFACE_NUMA_NODE}/" \
            --expression "s/@DAOS_IFACE_NAME@/${DAOS_AGENT_IFACE_NAME}/" \
            --expression "s/@DAOS_IFACE_DOMAIN_NAME@/${DAOS_AGENT_IFACE_DOMAIN_NAME}/" \
            /tmp/daos_agent.yml.in ; \
    else \
        sed --in-place --regexp-extended \
            --expression '/^@DAOS_IFACE_BEGIN@$/,/^@DAOS_IFACE_END@/d' \
            /tmp/daos_agent.yml.in ; \
    fi && \
    mv -f /tmp/daos_agent.yml.in /etc/daos/daos_agent.yml

# Set environment variables for DAOS
ENV DAOS_PKG_CONFIG_PATH=/usr/lib64/pkgconfig

# Install IO500
RUN git clone https://github.com/IO500/io500.git /opt/io500 && \
    cd /opt/io500 && \
    ./prepare.sh && \
    #./configure --with-daos=/usr && \
    make && \
    rm -rf /var/cache/dnf /root/.cache \

# Copy ini file
#COPY /home/yongju/daos-cmmh/config-daos.ini /opt/io500/

# Add IO500 to PATH
ENV PATH="/opt/io500/bin:${PATH}"

# Set the entrypoint
CMD ["/sbin/init"]

