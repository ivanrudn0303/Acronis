/**
 * Client
 * Client Requests log registration
 *
 * OpenAPI spec version: 1.0.0
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 3.3.3.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

/*
 * DefaultApi.h
 *
 * 
 */

#ifndef ORG_OPENAPITOOLS_CLIENT_API_DefaultApi_H_
#define ORG_OPENAPITOOLS_CLIENT_API_DefaultApi_H_


#include "../ApiClient.h"

#include <cpprest/details/basic_types.h>
#include "../ModelBase.h"

#include <boost/optional.hpp>

namespace org {
namespace openapitools {
namespace client {
namespace api {

using namespace org::openapitools::client::model;



class  DefaultApi 
{
public:

    explicit DefaultApi( std::shared_ptr<ApiClient> apiClient );

    virtual ~DefaultApi();

    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    pplx::task<void> logIdDelete(
        int32_t id
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    /// <param name="updatePeriod"></param>
    /// <param name="path"></param>
    pplx::task<void> logIdPost(
        int32_t id,
        int32_t updatePeriod,
        utility::string_t path
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    pplx::task<void> logIdPut(
        int32_t id
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* ORG_OPENAPITOOLS_CLIENT_API_DefaultApi_H_ */

