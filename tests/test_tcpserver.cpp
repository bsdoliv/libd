#include "TcpServer"
#include "gtest/gtest.h" 

class TcpServerImpl : public TcpServer
{
    void newConnection(TcpConnection *c);
    void readFinished(TcpConnection *c);
    void writeFinished(TcpConnection *c);
};

TEST_F(TcpServerTest, TestsNewConnection)
{
    TcpServerImpl ts;
    ts

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
