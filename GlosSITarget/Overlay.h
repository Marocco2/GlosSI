#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>

#include <spdlog/spdlog.h>

class Overlay {
  public:
    Overlay(sf::RenderWindow& window, const std::function<void()>& on_close);

    void setEnabled(bool enabled);
    bool isEnabled() const;
    bool toggle();
    void update();
    static void ProcessEvent(sf::Event evnt);
    static void Shutdown();
    static void AddLog(const spdlog::details::log_msg& msg);

    static void AddOverlayElem(const std::function<void()>& elem_fn);

  private:
    sf::RenderWindow& window_;
    sf::Clock update_clock_;
    bool enabled_ = true;
    std::function<void()> on_close_;
    void showLogs() const;
    [[nodiscard]] bool closeButton() const;

    struct Log {
        std::chrono::system_clock::time_point time;
        spdlog::level::level_enum level;
        std::string payload;
    };
    static inline std::vector<Log> LOG_MSGS_;
    static constexpr int LOG_RETENTION_TIME_ = 5;

    static inline std::vector<std::function<void()>> OVERLAY_ELEMS_;

};
