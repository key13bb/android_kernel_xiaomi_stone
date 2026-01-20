#ifndef _LINUX_KERNELSU_H
#define _LINUX_KERNELSU_H

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/dcache.h>

/* Forward declarations para estructuras que podrían faltar */
struct filename;
struct user_arg_ptr;
struct kstat;

#ifdef CONFIG_KSU_HOOKS

/* Declaraciones de las funciones de enlace (Hooks) */

/* execve */
extern void ksu_handle_execveat(int *fd, struct filename **filename_ptr,
                                void *argv, void *envp, int *flags);

/* faccessat */
extern void ksu_handle_faccessat(int *dfd, const char __user **filename_user,
                                 int *mode, int *flags);

/* statx */
extern void ksu_handle_stat(int *dfd, const char __user **filename_user,
                            int *flags, u32 *mask, struct kstat **stat);

/* vfs_read */
extern void ksu_handle_vfs_read(struct file **file_ptr, char __user **buf_ptr,
                                size_t *count_ptr, loff_t **pos);

/* input_handle_event (Opcional, si usas el módulo de seguridad de entrada) */
extern void ksu_handle_input_handle_event(unsigned int *type, unsigned int *code, int *value);

#else

/* Funciones vacías (Dummy) por si desactivas KSU en el futuro */
static inline void ksu_handle_execveat(int *fd, struct filename **filename_ptr, void *argv, void *envp, int *flags) {}
static inline void ksu_handle_faccessat(int *dfd, const char __user **filename_user, int *mode, int *flags) {}
static inline void ksu_handle_stat(int *dfd, const char __user **filename_user, int *flags, u32 *mask, struct kstat **stat) {}
static inline void ksu_handle_vfs_read(struct file **file_ptr, char __user **buf_ptr, size_t *count_ptr, loff_t **pos) {}
static inline void ksu_handle_input_handle_event(unsigned int *type, unsigned int *code, int *value) {}

#endif /* CONFIG_KSU_HOOKS */

#endif /* _LINUX_KERNELSU_H */
