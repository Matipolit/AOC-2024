import argparse
import sys

parser = argparse.ArgumentParser(description="Parses input arguments.")
parser.add_argument(
    "--part",
    type=int,
    choices=[1, 2],
    default=1,
    help="Specify the part of the program to run (1 or 2).",
)

args = parser.parse_args()
print(f"Running part {args.part} of the program")


def check_report_safety(checked_levels, recursion_level):
    direction_up = None
    print(f"Checking levels: {checked_levels} with len {len(checked_levels)}\n\n")
    levels_len = len(checked_levels)
    for level_idx in range(1, levels_len):
        print(f"level_idx: [{level_idx}] recursion: [{recursion_level}] Checking diff between {int(checked_levels[level_idx])} and {int(checked_levels[level_idx - 1])} direction up: {direction_up}")
        diff = int(checked_levels[level_idx]) - int(checked_levels[level_idx - 1])

        if diff == 0 or diff < -3 or diff > 3:
            if recursion_level == 1 or args.part == 1:
                return False
            else:
                new_levels = checked_levels[:level_idx - 1] + checked_levels[level_idx:]
                new_levels_2 = checked_levels[:level_idx] + checked_levels[level_idx + 1:]
                print(f"new levels: {new_levels} | {new_levels_2}")
                return check_report_safety(new_levels, 1) or check_report_safety(new_levels_2, 1)

        if diff < 0:
            if direction_up is True:
                if recursion_level == 1 or args.part == 1:
                    return False
                else:
                    new_levels = checked_levels[:level_idx - 1] + checked_levels[level_idx:]
                    new_levels_2 = checked_levels[:level_idx] + checked_levels[level_idx + 1:]
                    print(f"new levels: {new_levels} | {new_levels_2}")
                    return check_report_safety(new_levels, 1) or check_report_safety(new_levels_2, 1)
            else:
                if direction_up is None:
                    print("setting direction as down")
                    direction_up = False
        if diff > 0:
            if direction_up is False:
                if recursion_level == 1 or args.part == 1:
                    return False
                else:
                    new_levels = checked_levels[:level_idx - 1] + checked_levels[level_idx:]
                    new_levels_2 = checked_levels[:level_idx] + checked_levels[level_idx + 1:]
                    print(f"new levels: {new_levels} | {new_levels_2}")
                    return check_report_safety(new_levels, 1) or check_report_safety(new_levels_2, 1)
            else:
                if direction_up is None:
                    print("setting direction as up")
                    direction_up = True
    return True


safe = 0
for line in sys.stdin:
    if line != "":
        line = line.strip()
        levels = line.split(" ")
        if check_report_safety(levels, 0):
            print(f"{levels}: safe")
            safe += 1
        else:
            print(f"{levels}: unsafe")

print(f"Safe: {safe}")
