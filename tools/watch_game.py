import os
import subprocess
import sys
import time

WATCH_DIR = "../src/game"
TARGET = "GameLogic"

PRESET_NAME = sys.argv[1] if len(sys.argv) > 1 else "debug"

BUILD_CMD = [
    "cmake",
    "--build", "--preset", PRESET_NAME,
    "--target", TARGET
]


def get_latest_file_info(directory):
    latest_time = 0
    latest_file = ""
    
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith((".cpp", ".h", ".hpp")):
                filepath = os.path.join(root, file)
                mtime = os.path.getmtime(filepath)
                if (mtime > latest_time):
                    latest_time = mtime
                    latest_file = filepath
                
    return latest_time, latest_file


def check_syntax(filepath):
    if not filepath.endswith(".cpp"):
        return True

    print(f"Fast Syntax Check : {os.path.basename(filepath)}...")

    syntax_cmd = [
        "clang++", "-fsyntax-only", "-std=c++26",
        "-Isrc/core", "-Isrc/shared", "-Isrc/renderer",
        filepath
    ]

    try:
        result = subprocess.run(syntax_cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print("\n SYNTAX ERROR DETECTED (Build Aborted)")
            print("-"*40)
            print(result.stderr.strip())
            print("-"*40)
            return False
    except FileNotFoundError:
        print("clang++ not found in path for fast check, falling back to CMake...")
        return True


def watch():
    print("STFR Hot-Reload Watcher Started!")
    print(f"Watching : {WATCH_DIR}")
    print(f"CMake Preset : {PRESET_NAME}")
    print(f"Target : {TARGET}")

    last_mtime, _ = get_latest_file_info(WATCH_DIR)

    while True:
        time.sleep(1)
        current_mtime, changed_file = get_latest_file_info(WATCH_DIR)

        if (current_mtime > last_mtime):
            print(f"\n Change detected in {os.path.basename(changed_file)}!")

            if check_syntax(changed_file):
                print(f"Compiling {TARGET} via CMake...")
                start_time = time.time()
                result = subprocess.run(BUILD_CMD)
                elapsed = time.time() - start_time

                if result.returncode == 0:
                    print(f"Build successful in {elapsed:.2f}s! cr.h will now hot-reload.\n")
                else:
                    print("CMake link/compile failed.\n")
            else:
                print("CMake build skipped")

            last_mtime = get_latest_file_info(WATCH_DIR)[0]


if __name__ == "__main__":
    try:
        watch()
    except KeyboardInterrupt:
        print("\n🛑 Watcher stopped.")
