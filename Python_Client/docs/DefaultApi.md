# openapi_client.DefaultApi

All URIs are relative to *http://93.175.1.27:7800*

Method | HTTP request | Description
------------- | ------------- | -------------
[**log_id_delete**](DefaultApi.md#log_id_delete) | **DELETE** /Log/{id} | 
[**log_id_post**](DefaultApi.md#log_id_post) | **POST** /Log/{id} | 
[**log_id_put**](DefaultApi.md#log_id_put) | **PUT** /Log/{id} | 


# **log_id_delete**
> log_id_delete(id)



### Example
```python
from __future__ import print_function
import time
import openapi_client
from openapi_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = openapi_client.DefaultApi()
id = 56 # int | 

try:
    api_instance.log_id_delete(id)
except ApiException as e:
    print("Exception when calling DefaultApi->log_id_delete: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **id** | **int**|  | 

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: Not defined

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **log_id_post**
> log_id_post(id, update_period, path)



### Example
```python
from __future__ import print_function
import time
import openapi_client
from openapi_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = openapi_client.DefaultApi()
id = 56 # int | 
update_period = 4294967295 # int |  (default to 4294967295)
path = 'path_example' # str | 

try:
    api_instance.log_id_post(id, update_period, path)
except ApiException as e:
    print("Exception when calling DefaultApi->log_id_post: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **id** | **int**|  | 
 **update_period** | **int**|  | [default to 4294967295]
 **path** | **str**|  | 

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: Not defined

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **log_id_put**
> log_id_put(id)



### Example
```python
from __future__ import print_function
import time
import openapi_client
from openapi_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = openapi_client.DefaultApi()
id = 56 # int | 

try:
    api_instance.log_id_put(id)
except ApiException as e:
    print("Exception when calling DefaultApi->log_id_put: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **id** | **int**|  | 

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: Not defined

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

