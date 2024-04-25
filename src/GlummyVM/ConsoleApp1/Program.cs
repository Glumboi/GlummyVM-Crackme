// See https://aka.ms/new-console-template for more information

using System;

string userName;

Console.WriteLine("Enter username: ");
Console.ReadLine(userName);

char[] usernameChars = userName.ToCharArray();

string seg1 = usernameChars[userName.Length - 1].ToString() + 118 + usernameChars[userName.Length - 3] + 4;