import application
import sys

if __name__ == '__main__':
    app = application.Application()
    exit_status = app.run(sys.argv)
    sys.exit(exit_status)