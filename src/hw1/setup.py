from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'hw1'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*.launch.py'))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='group6',
    maintainer_email='hshi@todo.todo',
    description='Package for homework 1 CS7630',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'stupid = hw1.stupid:main',
            'joystick = hw1.joystick_listener:main'
        ],
    },

)
