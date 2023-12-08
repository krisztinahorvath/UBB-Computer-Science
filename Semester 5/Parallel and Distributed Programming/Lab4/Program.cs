using Lab4;
using System;
using System.Diagnostics;
using Lab4.Implementation;

public class Program
{
    static void Main()
    {
        var hosts = new List<string>
        {
            "httpbin.org/",
            "httpforever.com/",
            "detectportal.firefox.com/success.txt",
            "example.com/"
        };

        Console.WriteLine("*************************************************DIRECT CALLBACK*************************************************");
        DirectCallback.Run(hosts);

        Console.WriteLine("\n*************************************************TASKS*************************************************");
        TaskMechanism.Run(hosts);

        Console.WriteLine("\n*************************************************ASYNC/AWAIT TASKS*************************************************");
        AsyncTaskMechanism.Run(hosts);
    }
}