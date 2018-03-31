#ifndef ABSTRACTSERVERPROCESS_H
#define ABSTRACTSERVERPROCESS_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "canvas.h"
#include "classinfo.h"
#include "consoleobserver.h"
#include "libraryinfo.h"
#include "observer.h"
#include "serverpath.h"

namespace xpd {

/**
* @brief The Server Process Settings class.
*/

class ServerProcessSettings {
public:
    ServerProcessSettings() {}
};

typedef std::shared_ptr<Canvas> CanvasPtr;      /// @brief Pointer to abstract Canvas
typedef std::vector<CanvasPtr> CanvasList;      /// @brief Vector of pointers to abstract Canvases

typedef std::shared_ptr<ConsoleObserver> ConsoleObserverPtr;
typedef std::shared_ptr<Observer> ObserverPtr;
typedef std::vector<ObserverPtr> ObserverList;

typedef std::vector<LibraryInfo> LibraryList;
typedef std::vector<ClassInfo> ClassList;

class AbstractServer;

enum LogLevel {
    LOG_ERROR = 0,
    LOG_FATAL = 1,
    LOG_INFO = 2,
    LOG_DEBUG = 3,
    LOG_DUMP = 4
};

/**
 * @brief The Abstract Server Process class
 */
class AbstractServerProcess {
private:
    AbstractServerProcess();
    AbstractServerProcess(const AbstractServerProcess&);

protected:
    ServerProcessSettings settings_;
    CanvasList canvas_list_;
    ObserverList observer_list_;
    ServerPath path_;
    ConsoleObserverPtr console_observer_;
    const AbstractServer* parent_;
    LogLevel log_level_;

public:
    typedef std::runtime_error Exception;

public:
    AbstractServerProcess(const AbstractServer* parent, const ServerProcessSettings& s);
    virtual ~AbstractServerProcess();

    /// @brief Wrapper for dspSwitch(true)
    void dspOn() { dspSwitch(true); }
    /// @brief Wrapper for dspSwitch(false)
    void dspOff() { dspSwitch(false); }
    /// @brief Abstract. Switches audio processing on/off
    virtual void dspSwitch(bool value) = 0;

    /// @brief Returns ServerProcessSettings
    const ServerProcessSettings& settings() const;
    /// @brief Sets ServerProcessSettings
    void setSettings(const ServerProcessSettings& s);

    const ServerPath& path() const;
    ServerPath& path();

    /// @brief Adds observers to list
    void registerObserver(ObserverPtr o);
    /// @brief Removes specified observer fromlist
    void unregisterObserver(ObserverPtr o);

    // ?
    /// @brief Sets the console observer (currently one per server)
    virtual void registerConsoleObserver(ConsoleObserverPtr o);
    /// @brief Removes the console observer
    virtual void unregisterConsoleObserver(ConsoleObserverPtr o);

    // ?
    /// @brief Abstract
    virtual void addSearchPath(const std::string& path) = 0;

    /// @brief Abstract
    virtual bool loadLibrary(const std::string& libraryName) = 0;
    /// @brief Abstract
    virtual bool loadExternal(const std::string& externalName) = 0;

    /// @brief Lists loaded libraries
    virtual LibraryList loadedLibraries() const;
    /// @brief Lists loaded classes
    virtual ClassList loadedClasses() const;

    /// @brief Returns parent server object
    const AbstractServer* parent() const;

    /// @brief Post text to console. Uses std::out in this class
    virtual void post(const std::string& text = "");
    /// @brief Post error text to console. Uses std::out in this class
    virtual void error(const std::string& text = "");
    virtual void log(LogLevel level, const std::string& text);

    /// @brief returns log level
    LogLevel logLevel() const;
    /// @brief Sets log level
    virtual void setLogLevel(LogLevel l);

    /// @brief Abstract. Creates new canvas
    virtual CanvasPtr createCanvas() = 0;
    /// @brief Deletes canvas
    virtual bool deleteCanvas(CanvasPtr cnv);
    /// @brief Returns canvas list
    const CanvasList& canvasList() const;
    /// @brief Returns canvas count
    virtual size_t canvasCount() const;

    /// @brief Abstract. Send message to a named object (symbol)
    virtual void sendMessage(const std::string& object, const std::string& text) = 0;
};
}

//class PDSERVER_EXPORT ServerInstance // : Object ??
//{
//    static string getAudioAPIs();
//};

#endif // ABSTRACTSERVERPROCESS_H
