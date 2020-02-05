#ifdef __GNUC__
#  define ALIGNAS(TYPE) __attribute__ ((aligned(__alignof__(TYPE))))
#else
#  define ALIGNAS(TYPE) /* empty */
#endif

#ifndef I_FILE_WATCHER_H
#define I_FILE_WATCHER_H



#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

namespace advcpp
{

class IFolderWatcher
{
public:
    virtual ~IFolderWatcher() = 0;
    // IFolderWatcher();

    virtual void Read();

};

class NewFolderWatcher : public IFolderWatcher
{
public:
    NewFolderWatcher(char * a_folder_name);

    virtual void Read();

private:
    int m_fd;
    int m_wd;
    char * m_folder;
};

// todo add container of file names;
inline NewFolderWatcher::NewFolderWatcher(char * a_folder_name)
: m_fd()
, m_wd()
, m_folder(a_folder_name)
{
    m_fd = std::inotify_init();
    if(0 > m_fd)
    {
        throw;
    }
    m_wd = inotify_add_watch( m_fd, m_folder, IN_CREATE | IN_DELETE );
}


} // namespace advcpp

#endif // I_FILE_WATCHER_H