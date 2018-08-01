function Build(
    [ValidateSet('Release', 'Debug')]
    [Parameter(Mandatory=$true)]
    [string]$Configuration,
    [Parameter(Mandatory=$true)]
    [ValidateSet('x86', 'x64')]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$Solution
)
{
    &"c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" $Solution /p:Configuration=$Configuration /p:Platform=$Platform

    if (!$?)
    {
        Write-Error "c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe $Solution /p:Configuration=$Configuration /p:Platform=$Platform failed with exitcode $LASTEXITCODE"
        return;
    }
}
$ErrorActionPreference = "Stop"
$sln = Join-Path (git rev-parse --show-toplevel) "System-Monitor.sln";
Build -Configuration Debug -Platform x64 -Solution $sln
Build -Configuration Debug -Platform x86 -Solution $sln
Build -Configuration Release -Platform x64 -Solution $sln
Build -Configuration Release -Platform x86 -Solution $sln
