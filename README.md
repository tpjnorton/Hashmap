# Hashmap
A C++11/14 thread-safe hashmap created without the use of STL containers.

This implementation currently supports string-integer mapping, but a type-generic
version is in the works.

Operations supported:

  Insert
  Delete
  Lookup
  Re-Size

TO BUILD:

  Run the makefile provided.

NOTE: This hashmap uses separate chaining to deal with collisions.
While concurrent writes are supported across buckets in the table,
concurrent writes to the same bucket's collision-chain are not allowed.
