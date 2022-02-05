Yoo Min Cha
Computing IV
Professor Martin
16 March 2014
Homework PS5a

   The way I implemented ringbuffer was to use a vector of Int16s to hold the items to be queued in the buffer.  I used vectors
because they are easy to use and have very fast access time.  Dequeuing is slow for vectors and list would have been much faster 
for this purpose.  Vectors are faster for accessing the elements and also for enqueuing items.  I implemented this class based on
the specifications provided by the teacher on the ps5a assignment link.  Everything seems to be working correctly, I tested 
all the functions and members as thoroughly as I could.  