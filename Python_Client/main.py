import openapi_client
api = openapi_client.DefaultApi()
api.log_id_post(12, 5, '~/HelloLog.txt')
api.log_id_delete(12)
