param(
    [string]$TargetPath
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrWhiteSpace($TargetPath)) {
    Write-Error "Missing target directory. Usage: .\clone-skeleton.ps1 <new-directory-path>"
    exit 1
}

$sourceRoot = (Resolve-Path $PSScriptRoot).Path

$targetFullPath = if ([System.IO.Path]::IsPathRooted($TargetPath)) {
    [System.IO.Path]::GetFullPath($TargetPath)
} else {
    [System.IO.Path]::GetFullPath((Join-Path (Get-Location) $TargetPath))
}

if (Test-Path -LiteralPath $targetFullPath) {
    Write-Error "Target directory already exists: $targetFullPath"
    exit 1
}

$targetParent = Split-Path -Parent $targetFullPath
if ([string]::IsNullOrWhiteSpace($targetParent) -or -not (Test-Path -LiteralPath $targetParent)) {
    Write-Error "Target parent directory does not exist: $targetParent"
    exit 1
}

$sourceWithSlash = $sourceRoot.TrimEnd('\') + '\'
$targetWithSlash = $targetFullPath.TrimEnd('\') + '\'
if ($targetWithSlash.StartsWith($sourceWithSlash, [System.StringComparison]::OrdinalIgnoreCase)) {
    Write-Error "Target directory must be outside the skeleton source directory."
    exit 1
}

$excludedDirs = @(
    ".git",
    ".idea",
    "build",
    "dist",
    "_staging",
    "logs"
)

$excludedFilePatterns = @(
    "*.user",
    "*.suo",
    "*.vcxproj.user"
)

function Test-ExcludedRelativePath {
    param([string]$RelativePath, [bool]$IsDirectory)

    $parts = $RelativePath -split '[\\/]+' | Where-Object { $_ -ne "" }
    foreach ($part in $parts) {
        if ($excludedDirs -contains $part) {
            return $true
        }
        if ($part -like "cmake-build-*") {
            return $true
        }
    }

    if (-not $IsDirectory) {
        $fileName = Split-Path -Leaf $RelativePath
        foreach ($pattern in $excludedFilePatterns) {
            if ($fileName -like $pattern) {
                return $true
            }
        }
    }

    return $false
}

function Get-RelativePathFromSource {
    param([string]$FullPath)

    $absolutePath = [System.IO.Path]::GetFullPath($FullPath)
    $rootWithSlash = $sourceRoot.TrimEnd('\') + '\'

    if ($absolutePath.Equals($sourceRoot, [System.StringComparison]::OrdinalIgnoreCase)) {
        return ""
    }

    if (-not $absolutePath.StartsWith($rootWithSlash, [System.StringComparison]::OrdinalIgnoreCase)) {
        throw "Path is outside source directory: $absolutePath"
    }

    return $absolutePath.Substring($rootWithSlash.Length)
}

New-Item -ItemType Directory -Path $targetFullPath | Out-Null

try {
    Get-ChildItem -LiteralPath $sourceRoot -Force -Recurse -Directory |
        ForEach-Object {
            $relative = Get-RelativePathFromSource $_.FullName
            if (-not (Test-ExcludedRelativePath $relative $true)) {
                New-Item -ItemType Directory -Force -Path (Join-Path $targetFullPath $relative) | Out-Null
            }
        }

    Get-ChildItem -LiteralPath $sourceRoot -Force -Recurse -File |
        ForEach-Object {
            $relative = Get-RelativePathFromSource $_.FullName
            if (-not (Test-ExcludedRelativePath $relative $false)) {
                $destination = Join-Path $targetFullPath $relative
                $destinationParent = Split-Path -Parent $destination
                if (-not (Test-Path -LiteralPath $destinationParent)) {
                    New-Item -ItemType Directory -Force -Path $destinationParent | Out-Null
                }
                Copy-Item -LiteralPath $_.FullName -Destination $destination
            }
        }
} catch {
    Write-Error "Clone failed: $($_.Exception.Message)"
    exit 1
}

Write-Host "Skeleton cloned to: $targetFullPath"
