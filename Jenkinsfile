pipeline {
    agent any
    stages {
        stage('Build Backend') {
            steps { sh 'docker build -t backend-app backend' }
        }
        stage('Deploy Backends') {
            steps {
                sh '''
                docker network create app-network || true
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 --network app-network backend-app
                docker run -d --name backend2 --network app-network backend-app
                sleep 5
                '''
            }
        }
        stage('Deploy NGINX') {
            steps {
                sh '''
                docker build -t custom-nginx nginx
                docker rm -f nginx-lb || true
                docker run -d --name nginx-lb --network app-network -p 80:80 custom-nginx
                '''
            }
        }
    }
}
