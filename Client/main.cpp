#include <iostream>
#include <stdio.h>
#include "client/api/DefaultApi.h"

int main()
{
	org::openapitools::client::api::ApiClient client;
	std::shared_ptr<org::openapitools::client::api::ApiClient> ptr;
	org::openapitools::client::api::DefaultApi test(ptr);
	system("PAUSE");
	return 0;
}
