#!usr/bin/python

import hashlib
import fnmatch
import json
import subprocess
import os
import sys
import requests

src_path = os.path.abspath(sys.argv[1])

coveralls_request = {
    'service_name': 'travis-ci',
    'service_job_id': os.environ['TRAVIS_JOB_ID'],
    'source_files': []}

def parse_file(file):
    f = open(file, 'r')
    lines = f.readlines()
    header = lines[0].strip().split(':')
    abs_path = header[3]
    if (abs_path.startswith(src_path)):
        rel_path = abs_path[len(src_path) + 1:]
        md5 = hashlib.md5(open(file, 'rb').read()).hexdigest()
        
        coverage = []
        for line in lines[2:]:
            cols = line.strip().split(':')
            if (cols[0].endswith('-')):
                coverage.append(None)
            elif (cols[0].endswith('#') or cols[0].endswith('=')):
                coverage.append(0)
            else:
                coverage.append(int(cols[0]))       

        coveralls_request['source_files'].append({'name': rel_path, 'source_digest': md5, 'coverage': coverage})

gcov_cmd = ['gcov', '-d']
for root, dirs, files in os.walk('.'):
    for file in fnmatch.filter(files, '*.o'):
        full_path = os.path.join(root, file)
        print(full_path)
        gcov_cmd.append(full_path)

subprocess.call(gcov_cmd)

for root, dirs, files in os.walk('.'):
    for file in fnmatch.filter(files, '*.gcov'):
        print(file)
        parse_file(os.path.join(root, file))

with open('coveralls.json', 'w') as out:
    json.dump(coveralls_request, out)

with open('coveralls.json', 'rb') as f: 
    r = requests.post('https://coveralls.io/api/v1/jobs', files={'json_file': f})
    print(r.content)
