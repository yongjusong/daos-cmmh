"""
  (C) Copyright 2018-2022 Intel Corporation.

  SPDX-License-Identifier: BSD-2-Clause-Patent
"""
from performance_test_base import PerformanceTestBase


class IorEasy(PerformanceTestBase):
    # pylint: disable=too-many-ancestors
    # pylint: disable=too-few-public-methods
    """Test class Description: Run IOR Easy

    Use Cases:
            Create a pool, container, and run IOR Easy.

    :avocado: recursive
    """

    def test_performance_ior_easy_dfs_sx(self):
        """Test Description: Run IOR Easy, DFS, SX.

        :avocado: tags=all,full_regression
        :avocado: tags=hw,medium
        :avocado: tags=performance,ior,dfs
        :avocado: tags=IorEasy,test_performance_ior_easy_dfs_sx
        """
        self.run_performance_ior(namespace="/run/ior_sx/*", ior_params={'api': 'DFS'})

    def test_performance_ior_easy_libioil_sx(self):
        """Test Description: Run IOR Easy, dfuse + libioil, SX.

        :avocado: tags=all,full_regression
        :avocado: tags=hw,medium
        :avocado: tags=performance,ior,libioil
        :avocado: tags=IorEasy,test_performance_ior_easy_libioil_sx
        """
        self.run_performance_ior(namespace="/run/ior_sx/*", ior_params={'api': 'POSIX+IL'})

    def test_performance_ior_easy_libpil4dfs_sx(self):
        """Test Description: Run IOR Easy, dfuse + libpil4dfs, SX.

        :avocado: tags=all,full_regression
        :avocado: tags=hw,medium
        :avocado: tags=performance,ior,libpil4dfs
        :avocado: tags=IorEasy,test_performance_ior_easy_libpil4dfs_sx
        """
        self.run_performance_ior(namespace="/run/ior_sx/*", ior_params={'api': 'POSIX+PIL4DFS'})

    def test_performance_ior_easy_hdf5_sx(self):
        """Test Description: Run IOR Easy, HDF5, SX.

        :avocado: tags=all,full_regression
        :avocado: tags=hw,medium
        :avocado: tags=performance,ior,hdf5
        :avocado: tags=IorEasy,test_performance_ior_easy_hdf5_sx
        """
        self.run_performance_ior(namespace="/run/ior_sx/*", ior_params={'api': 'HDF5'})

    def test_performance_ior_easy_mpiio_sx(self):
        """Test Description: Run IOR Easy, MPIIO, SX.

        :avocado: tags=all,full_regression
        :avocado: tags=hw,medium
        :avocado: tags=performance,ior,mpiio
        :avocado: tags=IorEasy,test_performance_ior_easy_mpiio_sx
        """
        self.run_performance_ior(namespace="/run/ior_sx/*", ior_params={'api': 'MPIIO'})

    def test_performance_ior_easy_dfs_ec_16p2gx_stop_write(self):
        """Test Description: Run IOR Easy, DFS, EC_16P2GX, stop a rank during write.

        :avocado: tags=all,manual
        :avocado: tags=hw,medium
        :avocado: tags=performance
        :avocado: tags=IorEasy,test_performance_ior_easy_dfs_ec_16p2gx_stop_write
        """
        self.run_performance_ior(
            namespace="/run/ior_ec_16p2gx/*",
            stop_delay_write=0.5,
            ior_params={'api': 'DFS'})

    def test_performance_ior_easy_dfs_ec_16p2gx_stop_read(self):
        """Test Description: Run IOR Easy, DFS, EC_16P2GX, stop a rank during read.

        :avocado: tags=all,manual
        :avocado: tags=hw,medium
        :avocado: tags=performance
        :avocado: tags=IorEasy,test_performance_ior_easy_dfs_ec_16p2gx_stop_read
        """
        self.run_performance_ior(
            namespace="/run/ior_ec_16p2gx/*",
            stop_delay_read=0.5,
            ior_params={'api': 'DFS'})

    def test_performance_ior_easy(self):
        """Test Description: Run IOR Easy from an adjustable config.

        Meant to be used with launch.py --extra_yaml.

        :avocado: tags=all,manual
        :avocado: tags=hw,medium
        :avocado: tags=IorEasy,test_performance_ior_easy
        """
        self.run_performance_ior(namespace="/run/ior/*")
