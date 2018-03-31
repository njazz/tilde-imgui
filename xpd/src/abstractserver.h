#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "audiodevicemanager.h"
#include "mididevicemanager.h"

namespace xpd {

class AbstractServerProcess;

typedef std::shared_ptr<AbstractServerProcess> ProcessPtr;
typedef std::vector<ProcessPtr> ProcessList;

/**
 * @brief The Server Settings class
 */
class ServerSettings {
    std::string name_;

public:
    explicit ServerSettings(const std::string& name)
        : name_(name)
    {
    }

    /// @brief returns server name
    const std::string& name() const;

    bool operator==(const ServerSettings& s) const;
    bool operator!=(const ServerSettings& s) const;
};

/**
 * @brief The Abstract Server class.
 */
class AbstractServer {
protected:
    ProcessList process_list_;
    ServerSettings settings_;
    AudioDeviceManager audio_dev_;
    MIDIDeviceManager midi_dev_;

public:
    typedef std::runtime_error Exception;

public:
    AbstractServer(const ServerSettings& s);
    virtual ~AbstractServer();

    /// @brief Returns server settings
    const ServerSettings& settings() const;

    /// @brief Sets server settings
    void setSettings(const ServerSettings& s);

    /**
     * @brief Returns list of processes created by server.
     * @return
     */
    const ProcessList& processList() const;

    /**
     * @brief Creates new abstract server process.
     * @return Pointer to new process or null-ptr on error
     */
    virtual ProcessPtr createProcess() = 0;

    /**
     * @brief Returns server name
     */
    const std::string& name() const;
};

} // namespace xpd

#endif // ABSTRACTSERVER_H
