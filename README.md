# GameKiller.exe

This is it. I've had enough. I played too many games where my screen just froze
because of sloppy code or sloppy PC or whatever.

I decided to bring out the big guns.

Issue I want to solve:
- I have only one screen
- I use fullscreen instead of windowed because it usually gives more performances
- When a game freeze, reaching the Task Manager is sometimes impossible.

# My answer

I created my own Alt+F4 version, using Ctrl+Alt+F12 for now.
It's in the form of a tiny Windows shell notify app. It's tiny.

It waits for a Ctrl+Alt+F12, and then:
- It tries to send a nice WM_CLOSE to the current foreground app.
- If the app still runs after 1.5 seconds, it terminates the app.

In my use case, I'm quite sure the app usually does not listen to its messages anymore,
so it will more often than not feel the wrath of the TerminateProcess function.

Hope it works well for me!

## Disclamer

Some apps (especially some notepad instances) were brutally terminated during
the development of this tool. Hope the god of all software will still open
the door of software engineers heaven to me later.