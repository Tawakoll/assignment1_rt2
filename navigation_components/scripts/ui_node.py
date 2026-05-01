#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Pose
from std_msgs.msg import Empty

class UINode(Node):
    def __init__(self):
        super().__init__('ui_node')
        # Two publishers: one for targets, one for explicitly canceling
        self.target_pub = self.create_publisher(Pose, '/ui_target', 10)
        self.cancel_pub = self.create_publisher(Empty, '/ui_cancel', 10)
        self.get_logger().info("UI Node started. Ready for input.")

    def run_input_loop(self):
        while rclpy.ok():
            user_input = input("\nEnter 'x y theta' to move, or 'c' to cancel: ").strip().lower()

            # Handle cancellation explicitly
            if user_input == 'c':
                self.cancel_pub.publish(Empty())
                self.get_logger().info("Cancel request sent to Action Client.")
                continue

            # Handle coordinate input
            try:
                parts = user_input.split()
                if len(parts) != 3:
                    raise ValueError("Please provide exactly three numbers separated by spaces.")
                
                x, y, theta = map(float, parts)
                
                msg = Pose()
                msg.position.x = x
                msg.position.y = y
                msg.orientation.z = theta 
                
                self.target_pub.publish(msg)
                self.get_logger().info(f"Target ({x}, {y}, {theta}) sent to Action Client.")
                
            except ValueError as e:
                self.get_logger().error(f"Invalid input: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = UINode()
    
    try:
        node.run_input_loop()
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down UI Node...")
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()