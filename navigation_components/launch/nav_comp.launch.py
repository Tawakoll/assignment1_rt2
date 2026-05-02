from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container = ComposableNodeContainer(
        name='nav_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='navigation_components', 
                plugin='NavServer',
                name='nav_server'
            ),
            ComposableNode(
                package='navigation_components',
                plugin='NavClient',
                name='nav_client'
            )
        ],
        output='screen',
    )

    return LaunchDescription([container])