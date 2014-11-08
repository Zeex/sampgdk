from distutils.core import setup

setup(
  name='cidl',
  version='1.0',
  author='Zeex',
  author_email='zeex@rocketmail.com',
  url='https://github.com/Zeex/cidl',
  description='Parser for an IDL-like mini-language '
              'used in https://github.com/Zeex/sampgdk',
  license='Apache',
  requires='ply',
  py_modules=['cidl'],
)
