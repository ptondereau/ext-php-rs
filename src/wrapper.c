#include "wrapper.h"

zend_string *ext_php_rs_zend_string_init(const char *str, size_t len,
                                         bool persistent)
{
  return zend_string_init(str, len, persistent);
}

void ext_php_rs_zend_string_release(zend_string *zs)
{
  zend_string_release(zs);
}

const char *ext_php_rs_php_build_id() { return ZEND_MODULE_BUILD_ID; }

void *ext_php_rs_zend_object_alloc(size_t obj_size, zend_class_entry *ce)
{
  return zend_object_alloc(obj_size, ce);
}

void ext_php_rs_zend_object_release(zend_object *obj)
{
  zend_object_release(obj);
}
#if ZEND_DEBUG
size_t *ext_php_rs_emalloc(size_t size, const char *__zend_filename, const uint32_t __zend_lineno, const char *__zend_orig_filename, const uint32_t __zend_orig_lineno)
{
  zend_try
  {
    return _emalloc(size, __zend_filename, __zend_lineno, __zend_orig_filename, __zend_orig_lineno);
  }
  zend_catch
  {
    return 0;
  }
  zend_end_try();
}

size_t *ext_php_rs_efree(void *ptr, const char *__zend_filename, const uint32_t __zend_lineno, const char *__zend_orig_filename, const uint32_t __zend_orig_lineno)
{
  zend_try
  {
    _efree(ptr, __zend_filename, __zend_lineno, __zend_orig_filename, __zend_orig_lineno);

    return (size_t *)1;
  }
  zend_catch
  {
    return 0;
  }
  zend_end_try();
}
#else
size_t *ext_php_rs_emalloc(size_t size)
{
  zend_try
  {
    return _emalloc(size);
  }
  zend_catch
  {
    return 0;
  }
  zend_end_try();
}

size_t *ext_php_rs_efree(void *ptr)
{
  zend_try
  {
    _efree(ptr);

    return (size_t *)1;
  }
  zend_catch
  {
    return 0;
  }
  zend_end_try();
}
#endif

zend_executor_globals *ext_php_rs_executor_globals()
{
#ifdef ZTS
#ifdef ZEND_ENABLE_STATIC_TSRMLS_CACHE
  return TSRMG_FAST_BULK_STATIC(executor_globals_offset, zend_executor_globals);
#else
  return TSRMG_FAST_BULK(executor_globals_offset, zend_executor_globals *);
#endif
#else
  return &executor_globals;
#endif
}
