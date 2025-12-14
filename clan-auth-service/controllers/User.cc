#include "User.h"

using namespace clan::v1;

// Add definition of your processing function here

void User::login(const drogon::HttpRequestPtr &req,
                 std::function<void (const drogon::HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" login";
    //Authentication algorithm, read database, verify, identify, etc...
    //...
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid(); 
    auto resp=drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::getInfo(const drogon::HttpRequestPtr &req,
                   std::function<void (const drogon::HttpResponsePtr &)> &&callback,
                   std::string userId,
                   const std::string &token) const
{
    LOG_DEBUG<<"User "<<userId<<" get his information";

    //Verify the validity of the token, etc.
    //Read the database or cache to get user information
    Json::Value ret;
    ret["result"]="ok";
    ret["user_name"]="Jack";
    ret["user_id"]=userId;
    ret["gender"]=1;
    auto resp=drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}