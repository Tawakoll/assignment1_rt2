A ROS 2 package implementing an Action Server/Client architecture for 2D robot navigation. It allows users to send `(x, y, theta)` goals to a differential drive robot, supporting dynamic goal preemption and explicit cancellation.

## Node Architecture

*   **`nav_server`**: The action server. Subscribes to `/odom`, computes distance and orientation errors, handles goal preemption asynchronously, and publishes to `/cmd_vel`.
*   **`nav_client`**: The action client. Listens to UI commands and manages communication with the server.
*   **`ui_node.py`**: A Python terminal interface for sending coordinate targets or explicit cancel commands.
