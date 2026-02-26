pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                // Remove the CC_LAB-6/ prefix
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 backend-app
                docker run -d --name backend2 backend-app
                '''
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                // If you have an nginx folder, build it like this
                sh 'docker build -t nginx-lb nginx'
                sh 'docker rm -f nginx-container || true'
                sh 'docker run -d -p 80:80 --name nginx-container --link backend1 --link backend2 nginx-lb'
            }
        }
    }
    post {
        failure {
            echo 'Pipeline failed. Check console logs for errors.'
        }
    }
}
