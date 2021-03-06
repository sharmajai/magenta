# mx_handle_duplicate

## NAME

handle_duplicate - duplicate a handle

## SYNOPSIS

```
#include <magenta/syscalls.h>

mx_handle_t mx_handle_duplicate(mx_handle_t handle, mx_rights_t rights);
```

## DESCRIPTION

**handle_duplicate**() creates a duplicate of *handle*, referring
to the same underlying object, with new access rights *rights*.

To duplicate the handle with the same rights use **MX_RIGHT_SAME_RIGHTS**. If different
rights are desired they must be strictly lesser than of the source handle. It is possible
to specify no rights by using 0.

## RETURN VALUE

**handle_duplicate**() returns the duplicate handle on success (a
positive value), or an error code (negative).

## ERRORS

**ERR_BAD_HANDLE**  *handle* isn't a valid handle.

**ERR_INVALID_ARGS**  The *rights* requested are not a subset of *handle* rights.

**ERR_ACCESS_DENIED**  *handle* does not have **MX_RIGHT_DUPLICATE** and may not be duplicated.

**ERR_NO_MEMORY**  (Temporary) out of memory situation.

