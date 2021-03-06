// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#ifndef CEPH_LIBRBD_OBJECT_MAP_INVALIDATE_REQUEST_H
#define CEPH_LIBRBD_OBJECT_MAP_INVALIDATE_REQUEST_H

#include "include/int_types.h"
#include "librbd/AsyncRequest.h"

class Context;

namespace librbd {

class ImageCtx;

namespace object_map {

class InvalidateRequest : public AsyncRequest<> {
public:
  InvalidateRequest(ImageCtx &image_ctx, uint64_t snap_id, bool force,
                    Context *on_finish)
    : AsyncRequest(image_ctx, on_finish), m_snap_id(snap_id), m_force(force) {
  }

  virtual void send();

protected:
  virtual bool should_complete(int r);
  virtual int filter_return_code(int r) const {
    // never propagate an error back to the caller
    return 0;
  }

private:
  uint64_t m_snap_id;
  bool m_force;

};

} // namespace object_map
} // namespace librbd

#endif // CEPH_LIBRBD_OBJECT_MAP_INVALIDATE_REQUEST_H
