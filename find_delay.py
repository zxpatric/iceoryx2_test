import numpy as np
import re
from pathlib import Path


if __name__ == "__main__":
    file_path : Path = Path('./resources/example_data')
    max_delay : int = 0
    max_index : int = 0
    values : list = []
    with open(file_path, 'r') as file:
        for i, line in enumerate(file):
            match = re.search(r'with delay of (\d+) nanoseconds', line)
            if match:
                delay : int = int(match.group(1))
                if delay > max_delay:
                    max_delay = delay
                    max_index = i
                    values.append(delay)

    print(f'Item {max_index} has the max delay: {max_delay} ns')
    # print(f'Max delay: {max(values)} ns')
    print(f'Delay 90th percentile: {np.percentile(values, 90)} ns')
    print(f'Delay 50th percentile: {np.percentile(values, 50)} ns')
