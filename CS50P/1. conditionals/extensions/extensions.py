# Checks extension in filename provided and prints out corresponding MIME type

file_extension = input("Filename: ").strip().lower().rsplit('.',1)[1]

if file_extension == "gif":
    print("image/gif")
elif file_extension=="jpg" or file_extension=="jpeg":
    print("image/jpeg")
elif file_extension=="png":
    print("image/png")
elif file_extension=="pdf":
    print("application/pdf")
elif file_extension=="txt":
    print("text/plain")
elif file_extension=="zip":
    print("application/zip")
else:
    print("application/octet-stream")