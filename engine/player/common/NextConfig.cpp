
#include "common/NextConfig.h"

NextPlayerConfig::NextPlayerConfig() {
    mConfig = new PlayerConfig();
}

NextPlayerConfig::~NextPlayerConfig() {
    reset();
    if (mConfig) {
        delete mConfig;
        mConfig = nullptr;
    }
}

void NextPlayerConfig::reset() {
    if (!mConfig) {
        return;
    }

    memset(mConfig, 0, sizeof(PlayerConfig));

    mConfig->loop = 1;
    mConfig->max_fps = 61;
    mConfig->start_on_prepared = 1;
    mConfig->packet_buffering = 1;
    mConfig->dcc.max_buffer_size = MAX_QUEUE_SIZE;
    mConfig->pictq_size = VIDEO_PICTURE_QUEUE_SIZE_DEFAULT;
    mConfig->accurate_seek_timeout = MAX_ACCURATE_SEEK_TIMEOUT;
    mConfig->dcc.high_water_mark_in_bytes = DEFAULT_HIGH_WATER_MARK_IN_BYTES;
    mConfig->dcc.first_high_water_mark_in_ms = DEFAULT_FIRST_HIGH_WATER_MARK_IN_MS;
    mConfig->dcc.next_high_water_mark_in_ms = DEFAULT_NEXT_HIGH_WATER_MARK_IN_MS;
    mConfig->dcc.last_high_water_mark_in_ms = DEFAULT_LAST_HIGH_WATER_MARK_IN_MS;
    mConfig->dcc.current_high_water_mark_in_ms = DEFAULT_FIRST_HIGH_WATER_MARK_IN_MS;
}

NextPlayerConfig *NextPlayerConfig::operator->() {
    return mConfig;
}

NextPlayerConfig *NextPlayerConfig::get() {
    return mConfig;
}
