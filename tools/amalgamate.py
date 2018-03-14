import os
import re
import shutil

def main():
    out = os.path.join(os.getcwd(), 'out')
    try:
        os.mkdir(out)
    except Exception:
        pass

    filenames = [
        'sqlite/sqlite3.h',
        'sqlite/sqlite3.c',
        'yxml/yxml.h',
        'yxml/yxml.c',
        'feader.c'
    ]
    prog = re.compile('#include "([\w\d\.\/]+)"')
    with open(os.path.join(out, 'feader.c'), 'w') as outfile:
        for fname in filenames:
            with open(os.path.join(os.getcwd(), "src", fname.replace('/', os.path.sep))) as infile:
                for line in infile:
                    match = prog.match(line)
                    if line.strip() == '#include <yxml.h>' or (match and match.group(1) in filenames):
                        continue
                    outfile.write(line)
    with open(os.path.join(out, 'feader.h'), 'w') as outfile:
        with open(os.path.join(os.getcwd(), 'src', 'feader.h')) as infile:
            for line in infile:          
                    match = prog.match(line)
                    if match and match.group(1) in filenames:
                        continue
                    outfile.write(line)      
    shutil.copy(
        os.path.join(os.getcwd(), 'src', 'schema.sql'),
        os.path.join(os.getcwd(), 'out', 'schema.sql')
    )          

if __name__ == "__main__":
    print('Running main method')
    main()
    print ('Ran it!')
