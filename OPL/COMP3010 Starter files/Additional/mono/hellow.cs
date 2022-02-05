// Compile:
// 	mcs hellow.cs -pkg:dotnet
// Run:
// 	mono hellow.exe	
using System;
using System.Windows.Forms;

public class HelloWorld : Form
{
    static public void Main ()
    {
        Application.Run (new HelloWorld ());
    }

    public HelloWorld ()
    {
        Text = "Hello Mono World";
    }
}
