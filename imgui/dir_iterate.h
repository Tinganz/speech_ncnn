#ifndef __DIR_ITERATE__
#define __DIR_ITERATE__
#include <string>
#include <vector>

#ifndef EXPORT_API
#ifdef _WIN32
#define EXPORT_API __declspec( dllexport )
#else
#define EXPORT_API
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

    EXPORT_API int DIR_Iterate(std::string directory, std::vector<std::string>& filesAbsolutePath, std::vector<std::string>& filesname, std::vector<std::string>& suffix_filter, std::string prefix_filter,  bool suffix = true, bool prefix = false, bool recurrence = true, bool sort = true);

#ifdef __cplusplus
}
#endif
#endif /* __DIR_ITERATE__ */
