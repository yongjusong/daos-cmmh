"""
(C) Copyright 2018-2023 Intel Corporation.

SPDX-License-Identifier: BSD-2-Clause-Patent
"""

from soak_test_base import SoakTestBase


class SoakSmoke(SoakTestBase):
    """Test class Description: Runs soak smoke.

    :avocado: recursive
    """

    def test_soak_smoke(self):
        """Run soak smoke.

        Test ID: DAOS-2192

        Test Description:  This will create a slurm batch job that runs
        various jobs defined in the soak yaml.  It will run for no more than
        20 min

        :avocado: tags=all,full_regression
        :avocado: tags=hw,large,24
        :avocado: tags=soak,soak_smoke
        :avocado: tags=SoakSmoke,test_soak_smoke

        nothing

        """
        test_param = "/run/smoke/"
        self.run_soak(test_param)
