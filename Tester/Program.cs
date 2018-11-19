using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Vortex;
using Vortex.Graphics;


class Program
{
    static void Main(string[] args)
    {
        VWindow game = new VWindow(400,400, "Vortex Engine - Window");
        game.Run(30);
    }
}
