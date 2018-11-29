# openapi-client
Client Requests log registration

This Python package is automatically generated by the [OpenAPI Generator](https://openapi-generator.tech) project:

- API version: 1.0.0
- Package version: 1.0.0
- Build package: org.openapitools.codegen.languages.PythonClientCodegen

## Requirements.

Python 2.7 and 3.4+

## Installation & Usage
### pip install

If the python package is hosted on Github, you can install directly from Github

```sh
pip install git+https://github.com/GIT_USER_ID/GIT_REPO_ID.git
```
(you may need to run `pip` with root permission: `sudo pip install git+https://github.com/GIT_USER_ID/GIT_REPO_ID.git`)

Then import the package:
```python
import openapi_client 
```

### Setuptools

Install via [Setuptools](http://pypi.python.org/pypi/setuptools).

```sh
python setup.py install --user
```
(or `sudo python setup.py install` to install the package for all users)

Then import the package:
```python
import openapi_client
```

## Getting Started

Please follow the [installation procedure](#installation--usage) and then run the following:

```python
from __future__ import print_function
import time
import openapi_client
from openapi_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = openapi_client.DefaultApi(openapi_client.ApiClient(configuration))
id = 56 # int | 

try:
    api_instance.log_id_delete(id)
except ApiException as e:
    print("Exception when calling DefaultApi->log_id_delete: %s\n" % e)

```

## Documentation for API Endpoints

All URIs are relative to *http://93.175.1.27:7800*

Class | Method | HTTP request | Description
------------ | ------------- | ------------- | -------------
*DefaultApi* | [**log_id_delete**](docs/DefaultApi.md#log_id_delete) | **DELETE** /Log/{id} | 
*DefaultApi* | [**log_id_post**](docs/DefaultApi.md#log_id_post) | **POST** /Log/{id} | 
*DefaultApi* | [**log_id_put**](docs/DefaultApi.md#log_id_put) | **PUT** /Log/{id} | 


## Documentation For Models



## Documentation For Authorization

 All endpoints do not require authorization.


## Author



