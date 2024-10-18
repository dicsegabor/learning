[String[]]$nlow = @()
$lc = @{}
$t_lc = 0

$day_name = Read-Host -Prompt "Adjon meg egy napot (H, K, Sz, Cs, P)"
$free_teachers = @()

foreach($line in Get-Content $args[0]) {
    $line_splitted = $line.Split(", ")

    for(($i = 1); $i -lt $line_splitted.count; $i++) {
        $day = $line_splitted[$i].Split(" ")

        # Szerdai ora nelkuli tanarok keresese
        if($day[0] -eq "Sz" -And $day.count -eq 1) {
            $nlow += $line_splitted[0]
        }

        # Oraszamok osszegzese
        $t_lc += $day.count - 1

        # Elso ora nelkuli tanarok keresese az adott napon
        if($day[0] -eq $day_name -And (-Not ($day -contains 1))){
            $free_teachers += $line_splitted[0]
        }
    }
        # Oraszamok osszegzese
        $lc.add($line_splitted[0], $t_lc)
        $t_lc = 0
}

Write-Output "Azok a tanárok, akiknek nincs szerdán órája:"
if($nlow.count -eq 0) {
    Write-Output "NINCS"
}
else {
    $nlow | % {Write-Output " - $_"}
}

Write-Output "Óraszámok tanáronként:"
    $lc.GetEnumerator() | ForEach-Object{
        $message = ' - {0} {1}' -f $_.key, $_.value
        Write-Output $message
    }

Write-Output "Azok a tanárok, akiknek nincs ($day_name) napon első órája:"
$free_teachers | % {Write-Output " - $_"}