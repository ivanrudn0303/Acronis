# coding: utf-8

"""
    Client

    Client Requests log registration  # noqa: E501

    OpenAPI spec version: 1.0.0
    Generated by: https://openapi-generator.tech
"""


from __future__ import absolute_import
import sys
sys.path.append('C:/Users/user/Downloads/client2-20181123T183256Z-001\client2')
import unittest

import openapi_client
from openapi_client.api.default_api import DefaultApi  # noqa: E501
from openapi_client.rest import ApiException


class TestDefaultApi(unittest.TestCase):
    """DefaultApi unit test stubs"""

    def setUp(self):
        self.api = openapi_client.api.default_api.DefaultApi()  # noqa: E501

    def tearDown(self):
        pass

    def test_log_id_delete(self):
        """Test case for log_id_delete

        """
        pass

    def test_log_id_post(self):
        """Test case for log_id_post

        """
        pass

    def test_log_id_put(self):
        """Test case for log_id_put

        """
        pass


if __name__ == '__main__':
    unittest.main()