#include <drogon/drogon.h>
#include <iostream>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>
#include <drogon/orm/DbConfig.h>
#include <drogon/nosql/RedisClient.h>

int main()
{
    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 5555);

    // drogon::app().setLogLevel(trantor::Logger::kDebug);

    /*// drogon::app().addDbClient(pgConfig);
    std::shared_ptr<drogon::orm::DbClient> client;
    try
    {
        client = drogon::orm::DbClient::newPgClient("host=localhost port=5432 dbname=dragon_clans user=dragon password=dragonpass", 1, );
        // пример запроса
        // client->execSqlAsync("SELECT 1", [](const drogon::orm::Result &r)
        //                     { std::cout << "DB query OK!\n"; });
        std::cout << "Create db client" << std::endl;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "Postgres connection error: " << e.base().what() << std::endl;
        return 1;
    }

    client->execSqlAsync("SELECT * FROM users", [](const drogon::orm::Result &result)
                         {
                                std::cout << result.size() << " rows selected!" << std::endl;
                                int i = 0;
                                for (auto row : result)
                                {
                                    std::cout << i++ << ": clan name is " << row["username"].as<std::string>() << std::endl;
                                }
                                std::cout << ": user name is " << std::endl; }, [](const drogon::orm::DrogonDbException &e)
                         { std::cerr << "error:" << e.base().what() << std::endl; });
    */

    drogon::orm::PostgresConfig pgConfig;
    pgConfig.name = "default";
    pgConfig.host = "localhost";
    pgConfig.port = 5432;
    pgConfig.databaseName = "dragon_clans";
    pgConfig.username = "dragon";
    pgConfig.password = "dragonpass";
    pgConfig.connectionNumber = 1;

    drogon::app().addDbClient(pgConfig);

    drogon::nosql::RedisClientPtr redis;
    try
    {
        drogon::app().createRedisClient("127.0.0.1", 6379);
        LOG_INFO << "Redis client created";
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "Redis error: " << e.what();
        return 1;
    }

    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}