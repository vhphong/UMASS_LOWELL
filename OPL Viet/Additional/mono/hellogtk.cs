// Install gtk-2.0:
// 	sudo apt install gtk2.0
// Compile:
// 	mcs hellogtk.cs -pkg:gtk-sharp-2.0
// Run:
// 	mono hellogtk.exe
using Gtk;
using System;

class Hello
{
    static void Main ()
    {
        Application.Init ();

        Window window = new Window ("Hello Mono World");
        window.Show ();

        Application.Run ();
    }
}
