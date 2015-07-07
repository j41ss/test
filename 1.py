import os
import magic
#print os.version())

mime = magic.from_file( '1.mp3')
print mime
