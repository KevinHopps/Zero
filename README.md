# Zero
Rewrite files with 0s.
The idea being that rewriting the same bytes with 0s will securely erase the file so that it can be removed without fear of its contents being recovered.

Unfortunately, I have no way of knowing whether the underlying OS actually rewrites the same disk block or frees it and uses a new one.
