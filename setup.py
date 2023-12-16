from distutils.core import setup, Extension
import numpy

def main():
  setup(
    name="tolerate",
    version="1.0.0",
    description="tolerate module in Python",
    author="Mykhaylo",
    author_email="mdarmstr@ualberta.ca",
    install_requires=['numpy'],
    ext_modules=[Extension("tolerate", ["tolerate.c"], 
                 include_dirs=[numpy.get_include()])],
  )

if (__name__ == "__main__"):
    main()
