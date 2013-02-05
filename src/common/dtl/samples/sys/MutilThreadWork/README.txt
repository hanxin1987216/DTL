strategy是具体的策略调用接口。MutilThread和MutilThreadRead、MutilThreadWrite等构成策略模式。
     
      现在阶段：
            测试读文件用模式能编译通过。
     后面的任务是：
            把写文件，sendmail，json的解析都加到策略模式中。使客户端代码更加简洁。