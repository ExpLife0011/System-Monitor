$Env:COMPUTERNAME
function Get-IsAppveyor(){
    return ($Env:COMPUTERNAME -match "appveyor")
}
function Write-LogMessage(
    [Parameter(Mandatory=$true)]
    $Message,

    [Parameter(Mandatory=$true)]
    [ValidateSet("Information", "Warning", "Error")]
    $Category,

    $Details
) {
    if (Get-IsAppveyor) {
        Add-AppveyorMessage -Message $Message -Category $Category -Details $Details
    }
    else {
        if ($Category -eq "Information"){
            Write-Host $Message;
        } elseif($Category -eq "Warning") {
            Write-Warning $Message;
        } else {
            Write-Error $Message`
        }
    }
}


$pass = $true;
$path = git rev-parse --show-toplevel
Get-ChildItem -Recurse -Path $path `
    | Where-Object {
        $_.FullName -match "tests\\(x64|Win32)\\(Debug|Release)\\.*\.exe$";
    } `
    | Select-Object -ExpandProperty FullName `
    | ForEach-Object {
        if (Get-IsAppveyor) {
            $details = "vstest.console.exe $_ /UseVsixExtensions:true /logger:Appveyor"
        } else {
            $details = "vstest.console.exe $_ /UseVsixExtensions:true"
        }

        Invoke-Expression $details;
        $testResult = $?
        $pass = $pass -and $testResult;

        $m = $_ -match "(x64|Win32)";
        $platform = $Matches[0];

        $m = $_ -match "(Debug|Release)";
        $config = $Matches[0];


        if ($testResult) {
            Write-LogMessage -Message "Tests for", ($platform + "-" + $config), "passed" -Category Information -Details $details
        }
        else {
            Write-LogMessage -Message "Tests for", ($platform + "-" + $config), "failed" -Category Error -Details $details
        }
    }

if (!$pass) {
    exit 1
}