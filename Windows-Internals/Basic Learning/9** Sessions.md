What is a Session

* A session represents a set of resources shared by a group of preocesses
  * Windowing resources (Window Stations, Desktops, and windows)
  * Object namespace (for objects that can be named)
* A process can be a member of only one session
   ◇ Cannot change
* System starts with two sessions
   ◇ Session 0 is for the system and service processes
   ◇ Session 1 is for the interactive console session
* Additional sessions can be created locally ("switch user") or remotely (Remote Desktop Connection)

What's in a process
![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130252.png)

Info about atoms: 
https://learn.microsoft.com/en-us/windows/win32/dataxchg/about-atom-tables

Session related Debugger Commands

• Kernel mode
   * !session
      ▪ List sessions on the system and current session
   * !session -s n
      ▪ Change context to session n
  *   !sprocess [sessionid]
    
  Lists processes that belong to a session (uses the current session if sessionid is nor specified)
