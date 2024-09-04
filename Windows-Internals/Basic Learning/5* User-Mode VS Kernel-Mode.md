Threads access modes
User mode:
  * Allows access to non-operating system code & data only
  * No access to the hardware
  * Protects user applications from crashing the system

Kernel mode:
  * Privileged mode for use by the kernel and device drivers only
  * Allow access to all system resources
  * Can potentially crash the system

Windows doesn't provide any protection for private read/write system memory being used by components runninng in kernel mode. Once in kernel mode,Os an device-driver code has complete access to system-space memory and can bypass Windows security to access objects

This lack of protection emphasizes when installing third party drivers, especially if it's unsigned, that's why windows 2000 implements a driver-signing mechanism
