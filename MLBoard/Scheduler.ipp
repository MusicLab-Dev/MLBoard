/**
 * @ Author: Paul Creze
 * @ Description: Scheduler
 */

inline void Scheduler::tick(void) noexcept
{
    _hardwareModule.tick(*this);
    _networkModule.tick(*this);
}