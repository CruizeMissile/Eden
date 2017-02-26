from contextlib import contextmanager
import argparse
import os
import subprocess
import sys


parser = argparse.ArgumentParser()


def add_arguments():
    pass

@contextmanager
def pushd(new_dir):
    prev_dir = os.getcwd()
    os.chdir(new_dir)
    yield
    os.chdir(prev_dir)


def main():
# parsing command line arguments
    add_arguments()
    args = parser.parse_args()

    current_dir = os.path.dirname(os.path.realpath(__file__))

    if 'win32' == sys.platform:
        command = ['./Genie/windows/genie.exe', 'vs2015']
    elif 'darwin' == sys.platform:
        command = ['./Genie/darwin/genie', 'xcode4']
    else:
        command = ['./Genie/linux/genie', 'gmake']

    path = os.path.join(current_dir, "Scripts", "Project")
    with pushd(path):
        subprocess.call(subprocess.list2cmdline(command), shell=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
